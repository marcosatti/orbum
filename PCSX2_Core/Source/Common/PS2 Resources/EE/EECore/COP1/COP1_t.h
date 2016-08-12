#pragma once

#include "Common/PS2 Types/Registers/FPURegister32_t.h"
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
	In an 8x4 grid.
	*/
	std::shared_ptr<FPURegister32_t> FPR[32] = {
		std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(),
		std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(),
		std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(),
		std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>(), std::make_shared<FPURegister32_t>()
	};

	/*
	COP1 defines an accumulator register, used for multiply-accumulate type instructions.
	See EE Core Users Manual, page 157.
	*/
	std::shared_ptr<FPURegister32_t> ACC = std::make_shared<FPURegister32_t>();

	// Bitfield Register Implementations.
	/*
	COP1 defines 2 control registers, which are implemented as BitfieldRegisters.
	See EE Core Users Manual, page 158.
	*/
	std::shared_ptr<RegisterIRR_t> IRR = std::make_shared<RegisterIRR_t>(); // Also known as FCR[0].
	std::shared_ptr<RegisterCSR_t> CSR = std::make_shared<RegisterCSR_t>(); // Also known as FCR[31].


}; // class COP1