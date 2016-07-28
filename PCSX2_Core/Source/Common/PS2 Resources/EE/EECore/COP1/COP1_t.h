#pragma once

#include "Common/PS2 Types/Registers/FPURegister_t.h"
#include "Common/PS2 Resources/EE/EECore/COP1/Bitfield Registers/COP1_BitfieldRegisters_t.h"

class COP1_t {
public:
	/*
	COP1 refers to the FPU (floating-point unit) coprocessor.
	See EE Core Users Manual, chapter 8.
	*/

	// Register Implementations.

	/*
	COP1 defines 32 general purpose registers, called FPR's.
	See EE Core Users Manual, page 157.
	*/
	FPURegister_t FPR[32];

	/*
	COP1 defines an accumulator register, used for multiply-accumulate type instructions.
	See EE Core Users Manual, page 157.
	*/
	FPURegister_t ACC;

	/*
	COP1 defines 2 control registers, which are implemented as BitfieldRegisters.
	See EE Core Users Manual, page 158.
	*/
	struct
	{
		RegisterIRR_t IRR;
		RegisterCSR_t CSR;
	} BitfieldRegisters;


}; // class COP1