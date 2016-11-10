#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/Types/MIPSCoprocessor/MIPSCoprocessor_t.h"

class FPRegister32_t;
class BitfieldRegister32_t;
class FPURegister_IRR_t;
class FPURegister_CSR_t;

class EECoreFPU_t : public MIPSCoprocessor_t, public PS2ResourcesSubobject
{
public:
	explicit EECoreFPU_t(const PS2Resources_t* const PS2Resources);

	/*
	FPU refers to the FPU (floating-point unit) coprocessor.
	See EE Core Users Manual, chapter 8.
	*/

	// Register Implementations.

	/*
	FPU defines 32 general purpose registers, called FPR's.
	See EE Core Users Manual, page 157.
	*/
	std::shared_ptr<FPRegister32_t> FPR[32];

	/*
	FPU defines an accumulator register, used for multiply-accumulate type instructions.
	See EE Core Users Manual, page 157.
	*/
	std::shared_ptr<FPRegister32_t> ACC;

	// Bitfield Register Implementations.
	/*
	FPU defines 2 control registers, which are implemented as bitfield registers.
	See EE Core Users Manual, page 158.
	*/
	std::shared_ptr<FPURegister_IRR_t> IRR;
	std::shared_ptr<FPURegister_CSR_t> CSR;
	
	/*
	Array of above registers (needed by some EECore instructions to access by index). 
	Generally you will never access registers through this, only the PS2 OS will.
	Only FCR[0] and [31] are defined.
	*/
	std::shared_ptr<BitfieldRegister32_t> BitfieldRegisters[32];

	/*
	Checks if the FPU coprocessor (FPU) is usable. 
	Can be used by the component calling this to raise a EECoreException_t(coprocessor unusable) if not available.
	*/
	bool isCoprocessorUsable() const override;

};
