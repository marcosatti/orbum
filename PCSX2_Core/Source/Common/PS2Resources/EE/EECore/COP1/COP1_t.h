#pragma once

#include <Common/Interfaces/PS2ResourcesSubobject.h>
#include <memory>

class FPRegister32_t;
class BitfieldRegister32_t;
class RegisterIRR_t;
class RegisterCSR_t;

class COP1_t : public PS2ResourcesSubobject
{
public:
	explicit COP1_t(const PS2Resources_t* const PS2Resources);

	/*
	COP1 refers to the COP1 (floating-point unit) coprocessor.
	See EE Core Users Manual, chapter 8.
	*/

	// Register Implementations.

	/*
	COP1 defines 32 general purpose registers, called FPR's.
	See EE Core Users Manual, page 157.
	In an 8x4 grid.
	*/
	std::shared_ptr<FPRegister32_t> FPR[32];

	/*
	COP1 defines an accumulator register, used for multiply-accumulate type instructions.
	See EE Core Users Manual, page 157.
	*/
	std::shared_ptr<FPRegister32_t> ACC = std::make_shared<FPRegister32_t>();

	// Bitfield Register Implementations.
	/*
	COP1 defines 2 control registers, which are implemented as Registers.
	See EE Core Users Manual, page 158.
	*/
	std::shared_ptr<RegisterIRR_t> IRR;
	std::shared_ptr<RegisterCSR_t> CSR;
	
	/*
	Array of above registers (needed by some EECore instructions to access by index). Generally you will never access registers through this, only the PS2 OS will.
	Only FCR[0] and [31] are defined.
	*/
	std::shared_ptr<BitfieldRegister32_t> BitfieldRegisters[32];

	/*
	Checks if the COP1 coprocessor (COP1) is usable. Can be used by the component calling this to raise a EECoreException_t(coprocessor unusable) if not available.
	*/
	bool isCOP1Usable() const;
private:
};
