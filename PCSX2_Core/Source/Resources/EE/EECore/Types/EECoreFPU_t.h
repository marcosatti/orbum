#pragma once

#include <memory>

#include "Common/Types/MIPS/MIPSCoprocessor_t.h"

class Register32_t;
class BitfieldRegister32_t;
class EECoreFPURegister_IRR_t;
class EECoreFPURegister_CSR_t;
class EECoreCOP0_t;

/*
FPU refers to the FPU (floating-point unit) coprocessor.
See EE Core Users Manual, chapter 8.
*/
class EECoreFPU_t : public MIPSCoprocessor_t
{
public:
	EECoreFPU_t(const std::shared_ptr<EECoreCOP0_t> & cop0);

	/*
	FPU defines 32 general purpose registers, called FPR's.
	See EE Core Users Manual, page 157.
	*/
	std::shared_ptr<Register32_t> FPR[32];

	/*
	FPU defines an accumulator register, used for multiply-accumulate type instructions.
	See EE Core Users Manual, page 157.
	*/
	std::shared_ptr<Register32_t> ACC;

	// Bitfield Register Implementations.
	/*
	FPU defines 2 control registers, which are implemented as bitfield registers.
	See EE Core Users Manual, page 158.
	*/
	std::shared_ptr<EECoreFPURegister_IRR_t> IRR;
	std::shared_ptr<EECoreFPURegister_CSR_t> CSR;
	
	/*
	Array of above registers (needed by some EECore instructions to access by index). 
	Generally you will never access registers through this, only the PS2 OS will.
	Only FCR[0] and [31] are defined.
	*/
	std::shared_ptr<BitfieldRegister32_t> FCR[32];

	/*
	Checks if the FPU coprocessor (FPU) is usable. 
	Can be used by the component calling this to raise a EECoreException_t(coprocessor unusable) if not available.
	*/
	bool isCoprocessorUsable(const System_t context) const override;

private:
	/*
	Pointer to the EE Core COP0 coprocessor, needed for the Status register.
	*/
	std::shared_ptr<EECoreCOP0_t> COP0;

};
