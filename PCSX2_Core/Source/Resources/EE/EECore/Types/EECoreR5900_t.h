#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class Register128_t;
class Register32_t;
class ConstantRegister128_t;
class LinkRegister128_t;
class PCRegister32_t;

/*
The R5900 is the EE Core's CPU. 
It has been modified from a stock R5900 to include Sony specific instructions (multimedia instructions targeting 128-bit operations etc).
It uses a little-endian configuration.
*/
class EECoreR5900_t
{
public:
	EECoreR5900_t();

	/*
	The 32-bit Program Counter (PC) register. See EE Core Users manual, pg 61.
	Points to the current instruction virtual address.
	Must be initialised before LinkRegister and BD below due to dependency.
	*/
	std::shared_ptr<PCRegister32_t> PC;

	/*
	The R5900 general purpose registers (GPR's) are 128-bit long.
	The upper 64-bits are only used when specific instructions are run, such as using the EE Core specific multimedia instructions (parallel instructions). Example: PADDB.
	See EE Core Users Manual, pg 60.

	GPR defines the 32 GPR's contained within the R5900.
	This is implemented as an array of register numbers from GPR0 -> GPR31 (which translates to r0 -> r31).

	From the EE Core Users Manual, r0 and r31 are reserved:
	- r0 is the zero register, meaning it is always set to a constant 0. This is subclassed from Register128_t.
	- r31 is the link register used by the link and jump instructions. This is not to be used by other instructions.
	Special registers can be accessed through the EECoreR5900_t class, but are also included in the GPR array.
	*/
	std::shared_ptr<ConstantRegister128_t> ZeroRegister;
	std::shared_ptr<LinkRegister128_t> LinkRegister;
	std::shared_ptr<Register128_t> GPR[Constants::EE::EECore::R5900::NUMBER_GP_REGISTERS];

	/*
	The HI and LO registers. See EE Core Users manual, pg 60.
	These registers are used to hold the results of integer multiply and divide operations.
	They are 128-bit long.
	*/
	std::shared_ptr<Register128_t> HI; // The HI register. Divided into 2 64-bit segments: the upper 64-bits (HI1) and the lower 64-bits (HI0).
	std::shared_ptr<Register128_t> LO; // The LO register. Divided into 2 64-bit segments: the upper 64-bits (LO1) and the lower 64-bits (LO0).

	/*
	The Shift Amount (SA) register. See EE Core Users manual, pg 61.
	The SA register is used for holding funnel shift instruction results. See the EE Core instruction QFSRV for more details (SA is only used for this instruction).
	It is a 32-bit register.
	*/
	std::shared_ptr<Register32_t> SA;

}; // class R5900